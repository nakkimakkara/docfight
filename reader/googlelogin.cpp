#include "googlelogin.h"
#include "kqoauthmanager.h"
#include <QDebug>
#include <QCoreApplication>
#include "kqoauthrequest_xauth.h"
#include "kqoauthrequest.h"

GoogleLogin::GoogleLogin(QObject* parent)
    :QObject(parent)
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

    bOk = connect(oauthManager, SIGNAL(requestReady(QByteArray)),
            this, SLOT(onRequestReady(QByteArray)));

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

    qDebug() << "Access tokens now stored. You are ready to send Tweets from user's account!";


    KQOAuthParameters params;
    //params.insert("access_token", tokenSecret);
    params.insert("showfolders", "true");
    oauthManager->sendAuthorizedGetRequest(
        QUrl("https://docs.google.com/feeds/documents/private/full"), params);
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

void GoogleLogin::onRequestReady(QByteArray response) {
    qDebug() << "Response from the service: " << response;
    doccari = QString(response);
    emit docListChanged();
}

void GoogleLogin::xauth() {
    connect(oauthManager, SIGNAL(accessTokenReceived(QString,QString)),
            this, SLOT(onAccessTokenReceived(QString,QString)));

    KQOAuthRequest_XAuth *oauthRequest = new KQOAuthRequest_XAuth(this);
    oauthRequest->initRequest(KQOAuthRequest::AccessToken, QUrl("https://www.google.com/accounts/OAuthGetAccessToken"));
    oauthRequest->setConsumerKey("9PqhX2sX7DlmjNJ5j2Q");
    oauthRequest->setConsumerSecretKey("1NYYhpIw1fXItywS9Bw6gGRmkRyF9zB54UXkTGcI8");
    oauthRequest->setXAuthLogin(username, password);

    oauthManager->executeRequest(oauthRequest);
}

void GoogleLogin::sendTweet(QString tweet) {

    if( oauthSettings.value("oauth_token").toString().isEmpty() ||
        oauthSettings.value("oauth_token_secret").toString().isEmpty()) {
        qDebug() << "No access tokens. Aborting.";

        return;
    }

    oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("http://api.twitter.com/1/statuses/update.xml"));
    oauthRequest->setConsumerKey("9PqhX2sX7DlmjNJ5j2Q");
    oauthRequest->setConsumerSecretKey("1NYYhpIw1fXItywS9Bw6gGRmkRyF9zB54UXkTGcI8");
    oauthRequest->setToken(oauthSettings.value("oauth_token").toString());
    oauthRequest->setTokenSecret(oauthSettings.value("oauth_token_secret").toString());

    KQOAuthParameters params;
    params.insert("status", tweet);
    oauthRequest->setAdditionalParameters(params);

    oauthManager->executeRequest(oauthRequest);

    connect(oauthManager, SIGNAL(requestReady(QByteArray)),
            this, SLOT(onRequestReady(QByteArray)));
    connect(oauthManager, SIGNAL(authorizedRequestDone()),
            this, SLOT(onAuthorizedRequestDone()));
}

void GoogleLogin::showHelp() {
    QTextStream qout(stdout);
    qout << "GoogleLogin, version 0.95. Author: Johan Paul <johan.paul@d-pointer.com>\n"
         << "\n"
         << "Usage: GoogleLogin -[at] <tweet>\n"
         << " -a                Request for access tokens.\n"
         << " -x                Use Twitter xAuth to retrieve access tokens.\n"
         << " -t '<tweet>'      Send <tweet> to Twitter after retrieving access tokens\n"
         << "\n";
}
