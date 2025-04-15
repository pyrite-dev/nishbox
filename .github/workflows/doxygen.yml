name: "Publish Doxygen page"

on:
  push:
    branches:
    - master
  workflow_dispatch:
 
jobs:
  deploy:
    runs-on: ubuntu-latest
    permissions:
      contents: write
    steps:
    - name: Checkout
      uses: actions/checkout@v4
    - name: Install packages
      run: sudo apt-get install doxygen
    - name: Create directory
      run: mkdir -p build
    - name: Build engine document
      run: cd engine && doxygen && mv doc/html build/engine
    - name: Deploy
      uses: DamesIves/github-pages-deploy-action@v4
      with:
        token: ${{ secrets.GITHUB_TOKEN }}
        branch: gh-pages
        folder: build
