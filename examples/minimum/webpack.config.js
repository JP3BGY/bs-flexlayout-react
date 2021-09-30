const path = require('path');
const htmlWebpackPlugin = require('html-webpack-plugin');
const copyPlugin = require("copy-webpack-plugin");
const { Template } = require('webpack');

module.exports = {
  entry: './lib/js/src/index.js',
  output: {
    filename: 'main.js',
    path: path.resolve(__dirname, 'dist'),
  },
  devServer: {
    port: 4000,
    static: {
      directory: path.join(__dirname,'dist'),
    },
  },
  plugins: [
    new htmlWebpackPlugin({
      template: "./src/index.html"
    }),
    new copyPlugin(
      {
        patterns: [
          {from: "./node_modules/flexlayout-react/style/dark.css",to: "./"}
        ]
      }
    ),
  ],
};