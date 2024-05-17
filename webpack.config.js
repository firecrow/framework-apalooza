const path = require("path");

module.exports = {
  entry: './pre-dist/index.js',
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
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'dist'),
    library: "FFPalooza"
  },
};
