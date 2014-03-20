<?php
        //log function
        function logFile($filename,$msg){
	$fd = fopen($filename,"a");
	$str = "[".date("Y/m/d h:i:s",time())."]".$msg;
	fwrite($fd, $str."\n");
	fclose($fd);
        }

        $tokens=explode('/', $_GET['link']);
        $filename=$tokens[sizeof($tokens)-1];
        $folder='1/';
     
        if (file_exists($folder .$filename)) {

        logfile('log.txt', $filename.' file exists');
    
        header('Content-Type: image/jpeg');
        readfile($folder .$filename);
        } else {
                logfile('log.txt','file ' .$filename .' NOT exists');
        }
     
?>
