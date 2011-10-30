#include "googlelogin.h"
#include "kqoauthmanager.h"
#include <QDebug>
#include <QCoreApplication>
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
}

void GoogleLogin::updateDocumentList()
{
    QString updateUrl("https://docs.google.com/feeds/documents/private/full");
    KQOAuthParameters params;
    params.insert("showfolders", "true");
    pDocUpdateReply = oauthManager->sendAuthorizedGetRequest(QUrl(updateUrl), params);
}

void GoogleLogin::requestDocument(QString documentId)
{
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
    emit docListChanged();
}
