/*
 * list dependencies
 */
var express = require('express'),
	app = express(),
	server = require('http').createServer(app),
	io = require('socket.io').listen(server),
	serialPort = require('serialport').SerialPort;



/*
 * Serial Port Setup
 */

var portName = '/dev/ttyACM0';
var readData = ""; //Array to hold the values read from the port

var sp = new serialPort(portName, {
    baudRate : 57600,
    dataBits : 8,
    parity : 'none',
    stopBits: 1,
    flowControl : false,
});



io.sockets.on('connection', function(socket, debug){
    if(debug == false){
        socketServer.set('log level', 1);
    }
    socket.on('button', function(data){
        console.log("data from client: "+data.lampstatus);
        //serialPort.write(data);
    })
});


/*
 * Express setup
 */


// serve static files from index
app.configure(function(){
	app.use(express.static(__dirname + '/'));
});

// respon to web GET request on index.html
app.get('/', function (req, res){
	res.sendfile(__dirname + '/index.html');
});


server.listen(3000);
console.log('listen on port 3000')








