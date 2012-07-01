<?php


$tcp = uv_tcp_init();

uv_tcp_connect($tcp, uv_ip4_addr("0.0.0.0", 6667), function($stream, $status){
    var_dump($stream);
    uv_write($stream, "NICK chobot\n", function($stream, $stat) {
        echo "OK";
        uv_write($stream, "USER chobot h s :chobot\n", function($stream, $stat) {
            echo "OK";

            uv_write($stream, "join #debug\n", function($stream, $stat){});
            
            uv_read_start($stream, function($stream, $nread, $buffer) {
                $lines = explode("\n", $buffer);
                $nano = new NanoIRCParser();
                foreach ($lines as $line) {
                    $line = trim($line);

                    echo $line . PHP_EOL;
                    
                    if (empty($line)) {
                        continue;
                    }
                    
                    $result = $nano->parse($line);

                    var_dump($result);
                    if ($result["command"] == "PING") {
                        uv_write($stream, "PONG {$result['params']['0']}\n", function($stream, $stat){});
                    }
                }
            });
        });
    });
});

uv_run();

