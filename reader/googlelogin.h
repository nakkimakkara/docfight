#ifndef GOOGLELOGIN_H
#define GOOGLELOGIN_H

#include <QObject>
#include <QSettings>
#include <QSet>

class KQOAuthManager;
class KQOAuthRequest;
class QNetworkReply;

class GoogleLogin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString docList READ docList NOTIFY docListChanged)
    Q_PROPERTY(QString doc READ doc WRITE setDoc NOTIFY docChanged)
public:
    GoogleLogin(QObject* parent = NULL);
    virtual ~GoogleLogin();

    QString docList() const;

    Q_INVOKABLE void updateDocumentList();
    Q_INVOKABLE void requestDocument(QString documentId);
    Q_INVOKABLE void sendDocumentUpdate(QString document);

    Q_INVOKABLE void setDoc(QString doc);
    QString doc() const;

signals:
    void docChanged();
    void docListChanged();
    void connectionEstablished();
    void documentReady(QString documentId);

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
    QString docId;

    QString workingDoc;
    QNetworkReply* pDocUpdateReply;
    QSet<QNetworkReply*> sDocUpdateSet;
};

#endif // GOOGLELOGIN_H
