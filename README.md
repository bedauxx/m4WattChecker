# Overview

ミニ四駆に積んで走行中の消費電力の数値をbluetoothで送信するだけの回路です。
ミニ四駆に限らず電力を計測してbluetoothで送信できます。

## 必要なもの

* PC
    + macでもwinでもLinuxでも可(要bluetooth)
* Arduino IDE
* AdafruitのINA219用ライブラリ
    <https://github.com/adafruit/Adafruit_INA219>
* PRO Trinket 3V (もしくは同等品)
* INA219 Current Sensor
* 電源(3V) LI-POとかコイン電池とコネクタ
* BlueToothモジュール
* その他ユニバーサル基板とかリード線とかハンダとか

## 回路図

![回路図](https://github.com/bedauxx/m4WattChecker/wiki/images/current_sensor.png)


## 作り方

* BlueToothモジュールの設定を済ませる(機器名・通信速度など)
    + 使用するPCからbtで認識できることを確認する
* Arduino IDEにINA219のライブラリを導入
    + その他TrinketやI2C関係も動作するよう設定しておく
* TrinketにbtWattChecker.inoを書き込む
* 回路図に従って基板を作成

## 使用方法

* INA219のVin+をミニ四駆の電池+(モーター側)に接続
* INA219のVin-をミニ四駆の電池+側の接点に接続
    + ここでミニ四駆の電気系統をバイパスする為、上記2つの接点は絶縁する必要があります。薄い紙の片面にVin+用の接点(銅板など)を貼り、裏にVin-用の接点を貼りつけ、電池の+とターミナルの間に挟み込んでいます。vin+とvin-がショートすると正常に計測できません。
* 回路GNDをミニ四駆の電池-に接続する。
    + ここはGND用の接点を電池-とターミナルの間に挟むだけでよいです。
* 回路の電源をONにする。
* bluetoothを接続する。
    + bluetoothの接続は使用するbluetoothモジュールに依存します。モジュールのデータシートなどを確認して設定してください。
* Arduino IDEのシリアルポートを該当bluetoothモジュールに設定。
    + macの場合、/dev/cu.Bluetooth-Incoming-Portを使用するようです
* Arduino IDEのシリアルモニタを開く。
* ミニ四駆の電源スイッチをONにする
* 正常に動作した場合、電圧・消費電流が表示されます。


## 注意点

* 試作段階のため予告なく仕様変更するおそれがあります。
* INA219自体の電圧降下が若干あります。その為、モーターにかかる電圧が若干下がります。
* INA219の最大計測電流が3.2Aですが、MDPなどの大電流を要求するモーターを使用した際、通常走行で計測ピークを超えるようです。
* 試作の基板自体が30gほどありますので、走行時基板の重さが負荷になります。この点を考慮してマスダンパーの重量を減らすなどの必要があります。
* 作者環境では秒間4回(250ms)の計測が限界でした。回数を増やすと回路がフリーズします。おそらくPRO Trinket 3Vのスペックの問題だと思います。
* bluetoothモジュールは技適取得済みのものをご利用ください。

### その他
* TODO
    * センサー変更で最大計測電流を5A程度に変更
    * PC上の表示をシリアルモニタからnodeに変更
    * グラフ表示
    * スマートフォンでの接続・表示機能実装

* お願い
    * 電子回路に詳しい方をゆる募
    * ios/Androidのアプリエンジニアの方をゆる募 (React Nativeの使える方がいいな)
    * 間違いなどあったら教えてください
