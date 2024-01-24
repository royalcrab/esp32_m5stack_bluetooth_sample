const express = require('express');
const app = express();

// /publicディレクトリを静的ファイルのルートディレクトリとして指定
app.use(express.static(__dirname + '/public'));

// サーバーを起動するポートを指定（例：3000）
const PORT = 3000;

// サーバーを起動
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
