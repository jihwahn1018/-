var PythonShell = require('python-shell');

var options={
        mode: 'text',
        pythonPath: '',
        pythonOptions: ['-u'],
        scriptPath: '',
        args: ['value1']
};

function inter_fun(){
        PythonShell.PythonShell.run('make_random.py', options, function(err, number){
                if(err) throw err;

                console.log('results: %j', number);
        });
}

setInterval(inter_fun,600000);
