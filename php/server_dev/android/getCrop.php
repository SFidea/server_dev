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
        $folder1='det/';
        $folder2='crop/';
        $folder3='mesh/';
        $in_folder='uploads/';
   
        $output = shell_exec('python /var/www/facedetect.py ' .$in_folder. $filename .' ' .$folder1. $filename .' ' .$folder2. $filename .' crop');
        logfile('log.txt','output:' .$output);
   
   
        if (file_exists($folder2 .$filename)) {

        logfile('log.txt', $filename.' file exists');
    
        header('Content-Type: image/jpeg');
        readfile($folder2 .$filename);
        } else {
                logfile('log.txt','file ' .$filename .' NOT exists');
        }
     
?>
