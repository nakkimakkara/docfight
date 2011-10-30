#ifndef GOOGLELOGIN_H
#define GOOGLELOGIN_H

#include <QObject>
#include <QSettings>

class KQOAuthManager;
class KQOAuthRequest;
class QNetworkReply;

class GoogleLogin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString doclist READ docList NOTIFY docListChanged)
public:
    GoogleLogin(QObject* parent = NULL);
    virtual ~GoogleLogin();

    QString docList() const;

    Q_INVOKABLE void updateDocumentList();
    Q_INVOKABLE void requestDocument(QString documentId);

signals:
    void docListChanged();
    void connectionEstablished();
    void documentReady(QString documentId, QString documentXml);

public slots:
    void getAccess();
    void setUsername(QString name);
    void setPassword(QString pass);

private slots:
    void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
    void onAuthorizationReceived(QString token, QString verifier);
    void onAccessTokenReceived(QString token, QString tokenSecret);
    void onAuthorizedRequestDone();
    void onRequestReady(QNetworkReply*, QByteArray);

private:
    KQOAuthManager *oauthManager;
    KQOAuthRequest *oauthRequest;
    QSettings oauthSettings;

    QString username;
    QString password;

    QString doccari;

    QNetworkReply* pDocUpdateReply;
};

#endif // GOOGLELOGIN_H
