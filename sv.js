// npm init
// npm install express socket.io ip
//
const PORT = 3000;

var express = require('express');
var app = express();
var server = require('http').Server(app);	
var io = require('socket.io')(server);
var ip = require ('ip');

var esp8266_nsp = io.of('/esp8266')	
var middleware = require('socketio-wildcard')();
esp8266_nsp.use(middleware);

server.listen(PORT);


console.log("server running IP: " + ip.address() + ":" + PORT);
var led1 ,led2 ,led3,ledTest ;
led1 = 1;
led2 =1;
led3 = 1;

var data = [led1,led2,led3];
var ledData = {
		"led": data,
		
	};
app.get("/", function(req,res){
	data = [led1,led2,led3];
	ledData = {"led": data};
	res.send(ledData);
	console.log (JSON.stringify(ledData));
	ledTest  = ledData.led[1];
	console.log(""+ ledTest)

});	

app.get ("/:ledx/:states",function(req,res){
	var val1 = req.params.ledx;
	var val2 = req.params.states ;
		////////////// led 1
	if (val1 == 'led1'){
		if (val2 == 'off') led1 = 0;
		if (val2 == 'on') led1 = 1;
		data = [led1,led2,led3];
		ledData = {
		"led": data
	};
	res.send(ledData)
		io.emit('LED',ledData);
		console.log (JSON.stringify(ledData));	
	}
	
	////////////// led 2
	if (val1 == 'led2'){
		if (val2 == 'off') led2 = 0;
		if (val2 == 'on') led2 = 1;
		data = [led1,led2,led3];
		ledData = {
		"led": data
	};
		res.send(ledData)
		io.emit('LED',ledData);
		console.log (JSON.stringify(ledData));
	}
		////////////// led 3
	if (val1 == 'led3'){
		if (val2 == 'off') led3 = 0;
		if (val2 == 'on') led3  = 1;
		data = [led1,led2,led3];
		ledData = {"led": data};
		res.send(ledData)
		io.emit('LED',ledData);
		console.log (JSON.stringify(ledData));
	}
	if (val1 == 'faston'){
		led1 = 1;
		led2 = 1;
		led3 = 1;
		data = [led1,led2,led3];
		ledData = {"led": data};
		res.send(ledData)
		io.emit('LED',ledData);
		console.log (JSON.stringify(ledData));
	}
	if (val1 == 'fastoff'){
		led1 = 0;
		led2 = 0;
		led3 = 0;
		data = [led1,led2,led3];
		ledData = {"led": data};
		res.send(ledData)
		io.emit('LED',ledData);
		console.log (JSON.stringify(ledData));
	}
});

io.on("connection",function(){	
	console.log("welcome..................................");
		
	});

ledTest = 0;
var json={};
var interval1 = setInterval(function() {
		ledTest++;
		json = {
			pingIndex: ledTest,
			cordinate: [1,2,3],
			test: "string"
		}	;	
		io.emit('ping', json) 
		 //console.log("", ledTest)
		 //console.log(json)
	}, 1000)

// key , description 
esp8266_nsp.on('connection', function(socket) {
	console.log('esp8266 connected')
	
	socket.on('disconnect', function() {
		console.log("Disconnect socket esp826 6")
	});
	
	
	socket.on('ping', function(pong) {
		console.log("ping Nhan duoc", pong.pingIndex);
	console.log("");
	});
		
	socket.on('LED', function(ledPacket) {
		//console.log("esp8266 send ", ledPacket ,'\n')

		led1 = ledPacket.led[0];
		led2 = ledPacket.led[1];
		led3 = ledPacket.led[2];
		data = [led1,led2,led3]
		ledData = {"led": data};
		console.log ("Trang thai cac den: ",ledData);
	})
})