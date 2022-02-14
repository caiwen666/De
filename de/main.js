const electron = require("electron");
const ipcMain = electron.ipcMain;
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const globalShortcut = electron.globalShortcut;
let mainWindow;
const Menu = electron.Menu;

class Queue{
  constructor(){
    this.count = 0;//记录队列的数量
    this.lowestCount = 0;//记录当前队列顶部的位置
    this.items = [];//用来存储元素。
  }
  push(element){
    this.items[this.count] = element;
    this.count++;
  }
  pop(){
    if(this.empty()){
      return 'queue is null';
    }
    let resulte = this.items[this.lowestCount];
    delete this.items[this.lowestCount];
    this.lowestCount++;
    return resulte;
  }
  front(){
    return this.items[this.lowestCount];
  }
  empty(){
    return this.count - this.lowestCount === 0;
  }
  size(){
    return this.count - this.lowestCount;
  }
  clear(){
    this.count = 0;
    this.lowestCount = 0;
    this.items = [];
  }
  toString(){
    if(this.isEmpty())return "queue is null";
    let objString = this.items[this.lowestCount];
    for(let i = this.lowestCount+1; i < this.count;i++){
      objString = `${objString},${this.items[i]}`;
    }
    return objString;
  }
}
const queue=new Queue();

function sleep(ms) {
    return new Promise(resolve=>setTimeout(resolve, ms))
}

function createWindow() {
    // 隐藏菜单栏
    Menu.setApplicationMenu(null);
	mainWindow = new BrowserWindow({
        width: 500,
        height: 600,
        minWidth: 500,
        minHeight: 600,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        }
    });
    var fs = require('fs'); //文件读取
    mainWindow.loadURL('file://' + __dirname + '/gui/index.html');
    var data = fs.readFileSync('./config.json', 'utf8');
    //判断是否debug
    var obj = JSON.parse(data);
    if (obj.debug == "true") {
        mainWindow.webContents.openDevTools();
    }
    mainWindow.on("closed",
    function() {
        mainWindow = null;
    });
    ipcMain.on('main',
    function(event, arg) {
        console.log(arg);
        var obj1 = JSON.parse(arg);
        if (obj1.command == "test") {
            mainWindow.webContents.send('test', 'okok');
        }
        if (obj1.command == "zuixiao") {
            mainWindow.minimize();
        }
        if (obj1.command == "close") {
            mainWindow.close();
        }
    });
	ipcMain.on('back',
    async function(event, arg) {
		for(i=1;i<=queue.size();i++){
			mainWindow.webContents.send('command',queue.front());
			var copy = JSON.parse(JSON.stringify(queue.front()))
			queue.pop();
			queue.push(copy);
			await sleep(1000);
		}
    });
	var WebSocketServer = require('ws').Server,
		wss = new WebSocketServer({
			port: obj.port //监听接口
		});
	wss.on('connection', function(ws) {
		mainWindow.webContents.send('connect', 'aaa');
		queue.clear();
		ws.on('message', function(str,flags) {
			console.log("receive:"+str+"\n");
			var obj = eval('(' + str + ')');
			queue.push(obj);
			mainWindow.webContents.send('command',obj);
		});
		ws.on('close', function(close) {
			mainWindow.webContents.send('close', 'aaa');
		});
	});
}

app.on("ready", createWindow);
app.on("window-all-closed",
function() {
    if (process.platform != "darwin") {
        app.quit();
    }
});
app.on("activate",
function() {
    if (mainWindow === null) {
        createWindow();
    }
});