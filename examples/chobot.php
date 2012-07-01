<?php
date_default_timezone_set("Asia/Tokyo");

$tcp = uv_tcp_init();

uv_tcp_connect($tcp, uv_ip4_addr("86.65.39.15", 6667), function($stream, $status){
    var_dump($stream);
    uv_write($stream, "NICK chobot\n", function($stream, $stat) {
        echo "OK";
        uv_write($stream, "USER chobot h s :chobot\n", function($stream, $stat) {
            echo "OK";

            uv_write($stream, "join #php-uv\n", function($stream, $stat){});
            
            uv_read_start($stream, function($stream, $nread, $buffer) {
                $lines = explode("\n", $buffer);
                $nano = new NanoIRCParser();
                $pdo = new PDO("mysql:host=127.0.0.1; dbname=chobot", "root", "");
                $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                $stmt = $pdo->prepare("insert into chat(payload, time) values(:payload, CURRENT_TIMESTAMP());");
                foreach ($lines as $line) {
                    $line = trim($line);
                    echo $line . PHP_EOL;
                    if (empty($line)) {
                        continue;
                    }

                    $result = $nano->parse($line);

                    if ($result["command"] != "PING") {
                        $stmt->bindValue(":payload", $line);
                        $stmt->execute();
                    }

                    if ($result["command"] == "PING") {
                        uv_write($stream, "PONG {$result['params']['0']}\n", function($stream, $stat){});
                    }
                }
                unset($pdo);
		unset($nano);
            });
        });
    });
});

uv_run();

