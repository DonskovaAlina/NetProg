#include <iostream>
#include <ctime>
#include <arpa/inet.h>
#include <unistd.h>
#include <locale>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[256];

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        cerr << "Ошибка при создании сокета" << endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3306);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Ошибка при привязке сокета" << endl;
        close(s);
        return 1;
    }

    while (true) {
        ssize_t recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len == -1) {
            cerr << "Ошибка при получении данных" << endl;
            continue;
        }

        buf[recv_len] = '\0';
        cout << "Получено: " << buf << endl;

        time_t current_time = time(0);
        tm* local_time = localtime(&current_time);

        ostringstream timestream;
        timestream.imbue(locale("ru_RU.utf8"));
        timestream << put_time(local_time, "%A, %e %B %Y г., %H:%M:%S\n");
        string datetime = timestream.str();

        ssize_t sent_bytes = sendto(s, datetime.c_str(), datetime.size(), 0, (struct sockaddr*)&client_addr, addr_len);
        if (sent_bytes == -1) {
            cerr << "Ошибка при отправке данных" << endl;
        } else {
            cout << "Отправлено: " << datetime << endl;
        }
    }

    close(s);
    return 0;
}
