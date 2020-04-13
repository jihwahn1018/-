var express = require('express');
var app = express();
var moment = require('moment');
require('moment-timezone');
moment.tz.setDefault("Asia/Seoul");

var date = moment().format('YYYY-MM-DD HH:mm:ss');

mysql = require('mysql');
var connection = mysql.createConnection({
        host: 'localhost',
        user: 'me',
        password: 'me1',
        databse: 'mydb'
})
connection.connect();

function insert_sensor(device,value,seq){
        obj = {};
        obj.seq = seq;
        obj.device = device;
        obj.value = value;

        //console.log(obj);

        var query = connection.query('INSERT INTO mydb.temp_sensors SET ?', obj, function(err,rows,cols){
                if (err) throw err;
                console.log("database insertion ok= %j", obj);
        });
}

app.get('/', function(req, res) {
  res.end('Nice to meet you');
});

app.get('/temp_sample', function(req, res) {
        r = req.query;
        console.log("GET %j", r);

        var info = {
                "device_id" : r.device_id,
                "status" : "ok",
                "time" : date
        }

        insert_sensor(r.device_id, r.temperature_value, r.sequence_number);
        res.send(info);
        res.end('OK:' + JSON.stringify(req.query));
});

app.get('/temperature', function(req,res){
        r = req.query;
        var device_id = r.device_id;
        var r_length =0;
        if(device_id == ''){
                var query = connection.query('SELECT * FROM mydb.temp_sensors',function(err,result){
                        if (err) throw err;
                        res.send(result);
                        console.log('well done');
                });

        }else{
                var query = connection.query('SELECT * FROM mydb.temp_sensors WHERE device = ?',device_id,function(err,result){
                        if (err) throw err;
                        res.send(result);
                        console.log('well done');
                });

        }

});

var server = app.listen(8080, function () {
  var host = server.address().address
  var port = server.address().port
  console.log('listening at http://%s:%s', host, port)
});
