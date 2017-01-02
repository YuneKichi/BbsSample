# BBS用サンプル
## 1秒ごとに背景色を変更させるサンプル

"[C言語何でも質問掲示板](http://dixq.net/forum/viewforum.php?f=3)"
のスレッド
"[C#の疑問がいっぱい](http://dixq.net/forum/viewtopic.php?f=3&t=18718)"
用のC#でのサンプルです。

* ClassLibrary1はWindowsFormsApplication2とWpfApplication2で共通利用するModelクラスの定義
* WindowsFormsApplication1は、コードをForm1.csにべた書きした実装例
* WindowsFormsApplication2は、タイマーを別クラスに逃がした実装例
コンテキストの変更および数値から型への変更用に、ViewModelクラスを実装。
* WpfApplication1は、コードをMainWindow.xaml.csにべた書きした実装例
* WpfApplication2は、タイマーを別クラスに逃がした実装例
ViewModelを使わずに，Modelを直接バインドしてTriggerで背景色に変換している実装。

Visual Studio Community 2015 Update 3で作成・確認をしています。