var mysql = require('mysql');
var pool = mysql.createPool({
  connectionLimit : 10,
  host            : 'classmysql.engr.oregonstate.edu',
  user            : 'cs290_lioua',
  password        : '9226',
  database        : 'cs290_lioua'
});

module.exports.pool = pool;
