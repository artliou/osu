var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs361_adamsj5',
  password        : '4890',
  database        : 'cs361_adamsj5'
});

module.exports.pool = pool;
