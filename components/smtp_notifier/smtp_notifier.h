#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include <WiFiClient.h>

namespace esphome {
namespace smtp_notifier {

class SMTPNotifier : public Component {
 public:
  void setup() override;
  void loop() override {}

  void set_host(const std::string &host) { host_ = host; }
  void set_port(uint16_t port) { port_ = port; }
  void set_username(const std::string &username) { username_ = username; }
  void set_password(const std::string &password) { password_ = password; }
  void set_sender(const std::string &from) { from_ = from; }
  void set_recipient(const std::string &to) { to_ = to; }

  void send_mail(const std::string &subject, const std::string &message);

 protected:
  std::string host_;
  uint16_t port_;
  std::string username_;
  std::string password_;
  std::string from_;
  std::string to_;
};

}  // namespace smtp_notifier
}  // namespace esphome
