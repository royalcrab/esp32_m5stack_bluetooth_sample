
```
├── ESP32_BLE_multiserver_test
│   └── ESP32_BLE_multiserver_test.ino
├── LICENSE
├── M5StackCore2_BLE_multiserver_test
│   └── M5StackCore2_BLE_multiserver_test.ino
├── M5Stack_Bluetooth_Serial
│   └── M5Stack_Bluetooth_Serial.ino
├── Readme.md
└── server
    ├── index.js
    ├── package.json
    └── public
        └── index.html

```

- ESP32_BLE_multiserver_test:   ESP32 Dev Module 用　Bluetooth サンプル
- M5StackCore2_BLE_multiserver_test: M5Stack Core2　用　Bluetooth サンプル
- server: PC 側の通信テストプログラム ()
- M5Stack_Bluetooth_Serial: BluetoothSerial を使用した通信

M5Stack / ESP のコードは　Arduino 2.1.1 / esp Board Manager 2.0.14 以上を使用のこと

# server 以下の動かし方

node v18 以上が必要。

```bash
$ node -v
v18.11.0
$ yarn -v
1.22.19
$ yarn install
...
$ yarn dev
yarn run v1.22.19
$ node index.js
Server is running on port 3000
```

これでブラウザで `http://localhost:3000` を開く。

"Connet ESP" というボタンを押すとペアリングできる（はず）。"Send" を押すと 256 byte のデータが送信される。内容は　0 から 255 までの1ずつ増える数値 (byte)。





