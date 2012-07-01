php-nanoirc
===========

php-nanoirc binding

Useage
======

````php
<?php

$parser = new NanoIRCParser();
$result = $parser->parse(":zelazny.freenode.net 376 tkhrm :End of /MOTD command.\015\012");

var_dump($result);
/*
array(3) {
  ["prefix"]=>
  string(20) "zelazny.freenode.net"
  ["command"]=>
  string(3) "376"
  ["params"]=>
  array(2) {
    [0]=>
    string(5) "tkhrm"
    [1]=>
    string(21) "End of /MOTD command."
  }
}
*/
````

AUTHOR
======
Shuhei Tanuma

LICENSE
=======

MIT LICENSE
