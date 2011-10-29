#ifndef GOOGLELOGIN_H
#define GOOGLELOGIN_H

#include <QObject>
#include <QSettings>

class KQOAuthManager;
class KQOAuthRequest;

class GoogleLogin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString doclist READ docList NOTIFY docListChanged)
public:
    GoogleLogin(QObject* parent = NULL);
    virtual ~GoogleLogin();

    void xauth();
    void sendTweet(QString tweet);
    void showHelp();

    QString docList() const;

signals:
    void docListChanged();

public slots:
    void getAccess();
    void setUsername(QString name);
    void setPassword(QString pass);

private slots:
    void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
    void onAuthorizationReceived(QString token, QString verifier);
    void onAccessTokenReceived(QString token, QString tokenSecret);
    void onAuthorizedRequestDone();
    void onRequestReady(QByteArray);

private:
    KQOAuthManager *oauthManager;
    KQOAuthRequest *oauthRequest;
    QSettings oauthSettings;

    QString username;
    QString password;

    QString doccari;
};

#endif // GOOGLELOGIN_H
