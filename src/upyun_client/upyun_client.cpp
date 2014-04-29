#include "upyun_client.h"
#include "upyun_client_impl.h"

UpyunClient::UpyunClient(const QString &usr, const QString &pass, const QString &bucket):
    d_ptr(new UpyunClientPrivate(usr, pass, bucket))
{

}
