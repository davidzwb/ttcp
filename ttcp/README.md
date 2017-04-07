# ttpc 消息格式

客户端-->服务器：

header: length, number，总共 64 比特。

服务器-->客户端：

ack: length

客户端-->服务器：

message: count * data

每发送一个 data，接收一个 length 验证信息。

服务器-->客户端：

每接收一个 data，发送一个 length 验证信息。

最后，发送总 count ack

ack: count