#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring> // Для memset и strlen

int main() {
    int PORT = 1111;
    int buf_size = 256;
    struct sockaddr_in address;

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка при привязке" << std::endl;
        close(s);
        return 1;
    }

    if (listen(s, 5) < 0) {
        std::cerr << "Ошибка при прослушивании" << std::endl;
        close(s);
        return 1;
    }

    std::cout << "Ожидание соединений на порту " << PORT << "...\n" << std::endl;

    while (true) {
        int addrlen = sizeof(address);
        int new_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            std::cerr << "Ошибка при приеме соединения" << std::endl;
            continue;
        }

        char buf[buf_size];
        memset(buf, 0, buf_size); // Обнуляем буфер
        ssize_t recv_len = recv(new_socket, buf, buf_size - 1, 0);
        if (recv_len < 0) {
            std::cerr << "Ошибка при получении данных" << std::endl;
        } else {
            buf[recv_len] = '\0';
            std::cout << "Получено: " << buf << std::endl;
            std::string response = std::string(buf) + ", как дела?\n";
            send(new_socket, response.c_str(), response.length(), 0);
            std::cout << "Отправлено: " << response << std::endl;
        }

        close(new_socket);
    }

    close(s);
    return 0;
}
