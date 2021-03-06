# Overview

ミニ四駆に積んで走行中の消費電力の数値をbluetoothで送信するだけの回路です。
ミニ四駆に限らず電力を計測してbluetoothで送信できます。本体の重さ自体が走行時モーターの負荷になるため、なるべく最小・軽量構成になるようパーツを選定しています。
※「ミニ四駆」は株式会社タミヤの登録商標です。

## 前提条件

* Arduino初心者レベルの知識
* PCでの簡単なプログラミングスキル
* bluetoothの知識

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
* usb-シリアル変換(bluetoothモジュール設定用)
* その他ユニバーサル基板とかリード線とかハンダとか

## 試作機を運用して出た問題を修正した新バージョンを作成しました。
* センサーの変更（INA260）により15Aまでの計測が可能になりました。
* Li-Poのケーブルが走行の衝撃に耐えられず破損が頻発したのでボタン電池(CR2032)に変更しました。
* 試作機上のbtモジュールをBLE対応に変更しましたが、回路・ソフトウェアの変更はありません。
    + BLEを使用することでiosアプリ JBWaveでシリアルモニタ同様の機能が使用できました。

### 必要なもの(ina260バージョン)
* INA260 【高精度】I2Cディジタル電流・電圧・電力計モジュール(STRAWBERRY LINUX) <http://strawberry-linux.com/catalog/items?code=11260>
* INA260用ライブラリ <https://github.com/tronicgr/INA260-current-sensor>

## 回路図
* ina219バージョン
![回路図](https://github.com/bedauxx/m4WattChecker/wiki/images/current_sensor2_1.png)

* ina260バージョン
![回路図](https://github.com/bedauxx/m4WattChecker/wiki/images/current_sensor2_2.png)

## 作り方

* BlueToothモジュールの設定を済ませる(機器名・通信速度など)
    + ※モジュールによりますが、ATコマンドでの設定が必要です。ATコマンドがなんぞや？という方はググってみてください。
    + ※作者もATコマンドは全く知りませんでしたがググって数時間で設定できました。
    + 使用するPCからbtで認識できることを確認する
* Arduino IDEにカレントセンサのライブラリを導入
    + その他TrinketやI2C関係も動作するよう設定しておく
* ina219バージョンはTrinketにbtWattChecker.inoを書き込む
* ina260バージョンはTrinketにm4WattChecker.inoを書き込む
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
* Arduino IDEのシリアルモニタを開く。(通信速度は115200bpsに設定する)
* ミニ四駆の電源スイッチをONにする
* 正常に動作した場合、電圧・消費電流が表示されます。
    + 入力電圧が0Vのときは表示されません。ミニ四駆の電源をONにし、正常に電流が流れた際表示されます。
    + まれに5V以上の電圧を誤検知する為、5v以上の電圧時も表示をしない設定にしています。
* ※ina260バージョンは上記と回路図を参考に接続してください。こちらは15Aまで計測可能です。


## 注意点

* 試作段階のため予告なく仕様変更するおそれがあります。
* INA219自体の電圧降下が若干あります。その為、モーターにかかる電圧が若干下がります。
* INA219の最大計測電流が3.2Aですが、MDPなどの大電流を要求するモーターを使用した際、通常走行で計測ピークを超えるようです。
* 試作の基板自体が30gほどありますので、走行時基板の重さが負荷になります。この点を考慮してマスダンパーの重量を減らすなどの必要があります。
* 作者環境では秒間4回(250ms)の計測が限界でした。回数を増やすと回路がフリーズします。おそらくPRO Trinket 3Vのスペックの問題だと思います。
* 一番難しいのはbluetoothモジュールの初期設定かもしれません。使用するモジュールに合わせてググってください。
* ミニ四駆側に接続する接点の作成もシビアです。(とくに両軸シャーシ) 薄く丈夫な素材を使用してください。
    + モーターの電力を計測したいだけなら接点を組み込んで計測用シャーシを作成するほうが簡単かもしれません。その場合は電池+からモーターに接続するターミナルを切断し、接触しないよう注意して電池+側にINA219のvin+を、モーター側にvin-を、電池-側にGNDをそれぞれハンダづけしましょう。
* digisparkなどのもっと小さいarduino互換ボードを使用するとさらに小型化が可能になりますが、シリアル通信がソフトウェアシリアルを使用することになり、CPUの負荷がかさむ為今回は避けました。
* wroom32を使用すればbluetoothがビルトインされており、回路が単純化できます。また初期設定が簡単になる可能性もあります。ただし開発ボードが大きく重い為、重量バランスをさらに考慮する必要があります。
* bluetoothモジュールは技適取得済みのものをご利用ください。

### その他
* 公開の目的
    * 巧遅は拙速に如かず
    * 開発を続け完成度を上げて商品化するような性質のプロダクトではない
    * 開発に手を取られてミニ四駆を楽しむ時間に制約を受けたくない
    * 作者が電気回路の知識に乏しいため、詳しい方の協力を仰ぎたい

* TODO
    * センサー変更で最大計測電流を5A程度に変更
    * PC上の表示をシリアルモニタからnodeに変更
    * グラフ表示
    * スマートフォンでの接続・表示機能実装
    * モーターの電流のノイズを拾って走行中のモーターの回転数を取得(たぶんやらない、つかぼくのスキルでは無理)

* お願い
    * 電子回路に詳しい方をゆる募
    * ios/Androidのアプリエンジニアの方をゆる募 (React Nativeの使える方がいいな)
    * 間違いなどあったら教えてください

* 謝辞
    * 回路を積んだ機体の試走と調整を池袋DRIBARさん <http://www.dribar.net/> で行わせていただきました。ありがとうございました。
    * モーター慣らし・電流について多くをDRIBARミヤジ部長に教わりました。ありがとうございました。
    * ハヤシステムさんとDRIBAR店長アストさんの活動にインスパイアされ、制作しました。ありがとうございました。
    
