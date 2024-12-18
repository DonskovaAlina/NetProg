#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    char buf[256];
    char msg[] = "Привет";
    struct sockaddr_in self_addr; //для хранения адреса клиента
    self_addr.sin_family = AF_INET;
    self_addr.sin_port = 0;
    self_addr.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in srv_addr; //для хранения адреса сервера
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(1111);
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        cerr << "Ошибка при создании сокета" << endl;
        return 1;
    }

    int e = bind(s, (struct sockaddr*)&self_addr, sizeof(self_addr));
    if (e == -1) {
        cerr << "Ошибка при привязке" << endl;
        close(s);
        return 1;
    }

    e = connect(s, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if (e == -1) {
        cerr << "Ошибка при присоединении" << endl;
        close(s);
        return 1;
    }

    e = send(s, msg, strlen(msg), 0);
    if (e == -1) {
        cerr << "Ошибка при отправке данных" << endl;
        close(s);
        return 1;
    }

    cout << "Отправлено: " << msg << endl;

    int rc = recv(s, buf, sizeof(buf), 0);
    if (rc < 0) {
        cerr << "Ошибка при приеме данных" << endl;
        close(s);
        return 1;
    }

    buf[rc] = '\0';
    cout << "Получено: " << buf << endl;

    close(s);
    return 0;
}
