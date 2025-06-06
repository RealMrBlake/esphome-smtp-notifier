#include "smtp_notifier.h"
#include "esphome/core/log.h"
#include <base64.h>

namespace esphome {
namespace smtp_notifier {

static const char *const TAG = "SMTPNotifier";

void SMTPNotifier::setup() {
  ESP_LOGI(TAG, "SMTP Notifier initialized with server %s:%d", host_.c_str(), port_);
}

void SMTPNotifier::send_mail(const std::string &subject, const std::string &message) {
  WiFiClient client;
  if (!client.connect(host_.c_str(), port_)) {
    ESP_LOGE(TAG, "Failed to connect to SMTP server");
    return;
  }

  auto read_response = [&client]() {
    while (!client.available()) delay(10);
    String response = client.readStringUntil('\n');
    ESP_LOGD(TAG, "SMTP Response: %s", response.c_str());
  };

  read_response();
  client.printf("HELO %s\r\n", "esp32.local");
  read_response();

  client.printf("AUTH LOGIN\r\n");
  read_response();
  client.printf("%s\r\n", base64::encode(username_).c_str());
  read_response();
  client.printf("%s\r\n", base64::encode(password_).c_str());
  read_response();

  client.printf("MAIL FROM:<%s>\r\n", from_.c_str());
  read_response();
  client.printf("RCPT TO:<%s>\r\n", to_.c_str());
  read_response();
  client.printf("DATA\r\n");
  read_response();

  client.printf("Subject: %s\r\n", subject.c_str());
  client.printf("To: %s\r\n", to_.c_str());
  client.printf("From: %s\r\n", from_.c_str());
  client.printf("\r\n%s\r\n.\r\n", message.c_str());
  read_response();

  client.printf("QUIT\r\n");
  client.stop();

  ESP_LOGI(TAG, "Email sent to %s", to_.c_str());
}

}  // namespace smtp_notifier
}  // namespace esphome
