/*
 * list dependencies
 */
var express = require('express'),
    app = express(),
    server = require('http').createServer(app),
    io = require('socket.io').listen(server),
    serialPort = require('serialport').SerialPort,

    /*
     * Serial Port Setup
     */
    portName = '/dev/ttyACM0',
    //Array to hold the values read from the port
    readData = "",
    sp = new serialPort(portName, {
        baudRate: 57600,
        dataBits: 8,
        parity: 'none',
        stopBits: 1,
        flowControl: false,
    });


io.sockets.on('connection', function (socket, debug) {
    if (debug == false) {
        socketServer.set('log level', 1);
    }
    socket.on('button', function (data) {

        var status = data.lampstatus;
        console.log("data from client: " + status);

        sp.open(function () {
            console.log('open');
            sp.on('data', function(data) {
                console.log('data received: ' + data);
            });

            sp.write(status, function(err, result){
                if(err) console.log('[ERROR] '+err);
                console.log(result);
            });
        });
    })
});


/*
 * Express setup
 */


// serve static files from index
app.configure(function () {
    app.use(express.static(__dirname + '/'));
});

// respon to web GET request on index.html
app.get('/', function (req, res) {
    res.sendfile(__dirname + '/index.html');
});


server.listen(3000);
console.log('listen on port 3000')


