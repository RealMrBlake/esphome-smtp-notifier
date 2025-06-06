# ESPHome SMTP Notifier

A lightweight, production-ready SMTP component for ESPHome that allows your ESP32 devices to send plain-text email notifications directly via an SMTP server.

## ✉️ What is this?

This is a custom ESPHome component that enables direct email sending using SMTP from your ESP32 or ESP8266 devices without requiring an external webhook, Node-RED, or proxy.

## 🚀 Features

- 📧 Send plain-text emails via SMTP (no TLS)
- 🔐 Supports `AUTH LOGIN` authentication (Base64-encoded credentials)
- ⚙️ Configurable sender, recipient, subject, and message
- 🧠 Easy YAML integration
- ✅ No external services needed (pure ESP-side)

## ⚠️ Limitations

- No SSL/TLS support (for now)
- Works best with local or unencrypted SMTP servers (e.g. mail relay, Mailcow, Postfix with LAN access)
- No attachments or HTML content (yet)

## 🛠 Installation

1. Clone or download this repository.
2. Place the `smtp_notifier` folder inside your ESPHome project's `components` directory.

```

your-esphome-project/
└── components/
└── smtp\_notifier/
├── smtp\_notifier.h
└── smtp\_notifier.cpp

````

3. Reference it in your ESPHome YAML:

```yaml
external_components:
  - source:
      type: local
      path: ./components

smtp_notifier:
  id: mailer
  host: "mail.yourdomain.local"
  port: 25
  username: "esp@yourdomain.local"
  password: "yourpassword"
  from: "esp@yourdomain.local"
  to: "you@yourdomain.local"
````

4. Trigger emails via `lambda:` or `script:` blocks:

```yaml
script:
  - id: send_email_on_trigger
    then:
      - lambda: |-
          id(mailer).send_mail("Alarm Triggered", "The sensor has been activated.");
```

## ✅ Compatible Use Cases

* Local SMTP relays (Postfix, Mailcow, Mailu)
* Custom SMTP server without enforced encryption
* LAN-only ESP32 alerting without internet dependency

## 📄 License

MIT License – free to use, modify, and share.

## ❤️ Credits

Developed by [Louis](https://github.com/RealMrBlake) – inspired by the need for secure, offline-capable ESPHome alerts.
