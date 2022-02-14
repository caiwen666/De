//逻辑事件
const ipcRenderer = require('electron').ipcRenderer;
$("#guanbi").click(function (){
	// 发送信息给Main Process
	var json={ };
	json.command="close";
	var str=JSON.stringify(json);
	ipcRenderer.send('main', str);
});

$("#zuixiao").click(function (){
	// 发送信息给Main Process
	var json={ };
	json.command="zuixiao";
	var str=JSON.stringify(json);
	ipcRenderer.send('main', str);
});

$("#bu_back").click(function (){
	clear();
	ipcRenderer.send('back', "aa");
});

$("#bu_del").click(function (){
	clear();
});

ipcRenderer.on('connect', (event, arg) => {
	mdui.snackbar({
		message: '连接成功',
		position: 'left-bottom'
	});
});
ipcRenderer.on('close', (event, arg) => {
	mdui.snackbar({
		message: '连接断开',
		position: 'left-bottom'
	});
});
ipcRenderer.on('command', (event, arg) => {
	if(arg.arg=='add'){
		add(arg.id);
	}
	if(arg.arg=='link'){
		link(arg.from,arg.to,"e"+arg.id);
	}
	if(arg.arg=='mode'){
		vec=arg.vec;
	}
	if(arg.arg=='light'){
		if(arg.point==true){
			light(arg.id);
		}else{
			light("e"+arg.id);
		}
	}
	if(arg.arg=='remove'){
		if(arg.point==true){
			remove(arg.id);
		}else{
			remove("e"+arg.id);
		}
	}
	if(arg.arg=='offlight'){
		if(arg.point==true){
			offlight(arg.id);
		}else{
			offlight("e"+arg.id);
		}
	}
	if(arg.arg=='build'){
		mdui.snackbar({
			message: '成功构建图',
			position: 'left-bottom'
		});
		build();
	}
	if(arg.arg=='init'){
		init(arg.type);
	}
	if(arg.arg=='clear'){
		clear();
		mdui.snackbar({
			message: '图已被清除',
			position: 'left-bottom'
		});
	}
});