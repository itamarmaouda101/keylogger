<h1>linux keylogger</h1>
<p>
  this is a simple linux keylogger
  that is part of my rootkit project
</p>
<h2>what is it doing?</h2>
<p>the klm offers the</p>
<p> * save keystrokes in spesific file </p>
<p>hide from lsmod </p>
<p>unhide from lsmod </p>
<p>cover the tracks by cleaning kernel segments</p>
<p>remove the module from /sys/modules directory </p>
<h2>how to use</h2>
<p><b>for using the module u need to be super user</b></p>
<p>clone the repo, using git clone comannd</p>
<p>cd keylogger</p>
<p>make</p>
<p>sudo insmod kelogger.ko</p>
<h2>how to see the keyloging</h2>
<p>cd /sys/kernel/debug/keylogger</p>
<p>cat keyloging</p>
<h2>how to hide and unhide the module</h2>
<p><b>remember that after hiding the module will remove form /proc/modules and will not be recover, im working on fix it</b><p>
<p>cd /sys/kernel/debug/keylogger</p>
<p>./hide</p>
<h3>Tested on Linux ubuntu 5.4.0-52-generic </h3>
