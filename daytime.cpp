#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    char msg[] = "Вывод даты и времени\n";
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3306);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        cerr << "Ошибка при создании сокета" << endl;
        return 1;
    }
    
    ssize_t sent_bytes = sendto(s, msg, strlen(msg), 0, (const struct sockaddr*)&addr, sizeof(addr));
    if (sent_bytes == -1) {
        cerr << "Ошибка при отправке данных" << endl;
        close(s);
        return 1;
    }
    cout << "Отправлено: " << msg;
    
    char buf[256];
    socklen_t addr_len = sizeof(addr);
    ssize_t recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addr_len);
    if (recv_len == -1) {
        cerr << "Ошибка при получении данных" << endl;
        close(s);
        return 1;
    }
    
    buf[recv_len] = '\0';
    cout << "Получено: " << buf;
    
    close(s);
    return 0;
}
