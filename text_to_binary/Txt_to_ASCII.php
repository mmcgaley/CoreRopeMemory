<?php

$phrase = htmlspecialchars($_GET['phrase']);
echo "Your phrase: <br><br>&nbsp;&nbsp;&nbsp;&nbsp;";
echo $phrase;

echo "<br><br>  In ASCII binary:<br><br>";

$phrase_chars = str_split ($phrase);

echo "<table border=\"1\">";
foreach ($phrase_chars as $char) {
        echo "<tr><td>";
        echo $char;
        echo "</td><td>&nbsp;&nbsp;</td>";
        $digits = strval(decbin(ord($char)));

        # if the binary result only has six digits
        if (ord($char) < 64) {
                echo "<td>0</td>";
        }
        $digits_array = str_split ($digits);
        foreach ($digits_array as $digitchar) {
                echo "<td>";
                echo $digitchar;
                echo "</td>";
        }
        echo "</tr>";
}
echo "</table>";
?>
