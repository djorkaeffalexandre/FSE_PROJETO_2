#ifndef SERVER_H_
#define SERVER_H_

typedef struct {
  double temperature;
  double humidity;
} Bme280;

void* recv_message();
void send_message();

#endif /* SERVER_H_ */
