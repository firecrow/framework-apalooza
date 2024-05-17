const path = require('path');

module.exports = {
  entry: './dist/index.js',
  module: {
    rules: [
      {
        test: /(\.ts?$|\.tsx?$)/,
        use: 'ts-loader',
        exclude: /node_modules/,
      },
    ],
  },
  devtool: "source-map",
  resolve: {
    extensions: ['.js'],
  },
  output: {
    filename: 'app.js',
    path: path.resolve(__dirname, 'public'),
    library: "FwpReact"
  },
};
