#include "googlelogin.h"
#include "kqoauthmanager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include "kqoauthrequest_xauth.h"
#include "kqoauthrequest.h"

GoogleLogin::GoogleLogin(QObject* parent)
    :QObject(parent), pDocUpdateReply(NULL)
{
    username = "harri.hakkeri@gmail.com";
    password = "hackfest2011";

    oauthRequest = new KQOAuthRequest;
    oauthRequest->setScope("http://docs.google.com/feeds/");

    oauthRequest->setEnableDebugOutput(true);

    oauthManager = new KQOAuthManager(this);

    oauthManager->setHandleUserAuthorization(true);
}

GoogleLogin::~GoogleLogin()
{
    delete oauthRequest;
    delete oauthManager;
}

QString GoogleLogin::docList() const
{
    return doccari;
}

void GoogleLogin::getAccess()  {
    bool bOk = connect(oauthManager, SIGNAL(temporaryTokenReceived(QString,QString)),
            this, SLOT(onTemporaryTokenReceived(QString, QString)));
    Q_ASSERT(bOk);

    bOk = connect(oauthManager, SIGNAL(authorizationReceived(QString,QString)),
            this, SLOT( onAuthorizationReceived(QString, QString)));
    Q_ASSERT(bOk);

    bOk = connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)),
            this, SLOT(onAccessTokenReceived(QString,QString)));
    Q_ASSERT(bOk);

    bOk = connect(oauthManager, SIGNAL(requestReady(QNetworkReply*, QByteArray)),
            this, SLOT(onRequestReady(QNetworkReply*, QByteArray)));

    Q_ASSERT(bOk);

    QString requestUrl("https://www.google.com/accounts/OAuthGetRequestToken");
    oauthRequest->initRequest(KQOAuthRequest::TemporaryCredentials, QUrl(requestUrl));
    oauthRequest->setConsumerKey("33453548285.apps.googleusercontent.com");
    oauthRequest->setConsumerSecretKey("xHR98tIiZGf5-FmP4tdn-09y");


    KQOAuthParameters params;
    params.insert("scope",
                  "https://docs.google.com/feeds/");
    oauthRequest->setAdditionalParameters(params);

    oauthManager->setHandleUserAuthorization(true);

    oauthManager->executeRequest(oauthRequest);
}

void GoogleLogin::onTemporaryTokenReceived(QString token, QString tokenSecret)
{
    qDebug() << "Temporary token received: " << token << tokenSecret;

    QUrl userAuthURL("https://www.google.com/accounts/OAuthAuthorizeToken");

    if( oauthManager->lastError() == KQOAuthManager::NoError) {
        qDebug() << "Asking for user's permission to access protected resources. Opening URL: " << userAuthURL;
        oauthManager->getUserAuthorization(userAuthURL);
    }

}

void GoogleLogin::onAuthorizationReceived(QString token, QString verifier) {
    qDebug() << "User authorization received: " << token << verifier;

    oauthManager->getUserAccessTokens(QUrl("https://www.google.com/accounts/OAuthGetAccessToken"));
    if( oauthManager->lastError() != KQOAuthManager::NoError) {
        QCoreApplication::exit();
    }
}

void GoogleLogin::onAccessTokenReceived(QString token, QString tokenSecret) {
    qDebug() << "Access token received: " << token << tokenSecret;

    oauthSettings.setValue("oauth_token", token);
    oauthSettings.setValue("oauth_token_secret", tokenSecret);

    qDebug() << "Access tokens now stored!";

    emit connectionEstablished();
    updateDocumentList();
}

void GoogleLogin::setDoc(QString doc)
{
    if (workingDoc != doc)
    {
        workingDoc = doc;
        sendDocumentUpdate(doc);
        emit docChanged();
    }
}

QString GoogleLogin::doc() const
{
    return workingDoc;
}

void GoogleLogin::updateDocumentList()
{
    QString updateUrl("https://docs.google.com/feeds/documents/private/full");
    KQOAuthParameters params;
    params.insert("showfolders", "true");
    pDocUpdateReply = oauthManager->sendAuthorizedRequest(QUrl(updateUrl),
                                                          params,
                                                          KQOAuthRequest::GET);
}

void GoogleLogin::sendDocumentUpdate(QString document)
{
    QString reqUrl(QString("https://docs.google.com/feeds/media/private/full/document%3A")
                   + docId);
    KQOAuthParameters params;

    QString rawData(document);

    oauthManager->sendAuthorizedRequest(reqUrl,
                                        params,
                                        KQOAuthRequest::PUT,
                                        rawData.toAscii());

}

void GoogleLogin::requestDocument(QString documentId)
{
    // Ensure document-prefix is stripped
    const QString docPrefix("document:");
    if (documentId.indexOf(docPrefix) == 0)
    {
        documentId = documentId.right(documentId.count() - docPrefix.count());
    }

    QString reqUrl(QString("https://docs.google.com/feeds/download/documents/Export"));

    KQOAuthParameters params;
    params.insert("exportFormat", "html");
    params.insert("id", documentId);
    docId = documentId;
    QNetworkReply* reply = oauthManager->sendAuthorizedRequest(reqUrl,
                                                               params,
                                                               KQOAuthRequest::GET);
    sDocUpdateSet.insert(reply);
}

void GoogleLogin::setUsername(QString name)
{
    username = name;
}

void GoogleLogin::setPassword(QString pass)
{
    password = pass;
}

void GoogleLogin::onAuthorizedRequestDone() {
    qDebug() << "Request sent to Twitter!";
    QCoreApplication::exit();
}

void GoogleLogin::onRequestReady(QNetworkReply* reply, QByteArray response) {
    qDebug() << "Response from the service: " << response;
    doccari = QString(response);

    if (pDocUpdateReply == reply)
    {
        qDebug() << "Received document list update: " << QString(response);
        emit docListChanged();
        pDocUpdateReply = NULL;
    }
    else if (sDocUpdateSet.contains(reply))
    {
        qDebug() << "Received document fetch reply: " << QString(response);
        workingDoc = response;
        sDocUpdateSet.remove(reply);
        emit docChanged();
    }
}
