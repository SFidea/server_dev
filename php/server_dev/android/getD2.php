<?php
        //log function
        function logFile($filename,$msg){
	$fd = fopen($filename,"a");
	$str = "[".date("Y/m/d h:i:s",time())."]".$msg;
	fwrite($fd, $str."\n");
	fclose($fd);
        }

        $tokens=explode('/', $_GET['name']);
        $filename=$tokens[sizeof($tokens)-1];
        $folder='/var/www/php/server_dev/data/stasm_images/';
   
        //call image detection
        // Create image instances
        $dest = imagecreatefromstring(file_get_contents($filename));
        $src = imagecreatefromstring(file_get_contents($folder .$filename));

        // Copy and merge
        imagecopymerge($dest, $src, 10, 10, 0, 0, 100, 47, 75);

        // Output and free from memory
        header('Content-Type: image/jpeg');
        imagejpeg($dest);
        imagedestroy($dest);
        imagedestroy($src);
?>
