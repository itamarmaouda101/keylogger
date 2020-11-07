<h1>linux keylogger</h1>
<p>
  this is a simple linux keylogger
  that is part of my rootkit project
</p>
<h2>what is it doing?</h2>
<p>the klm offers the</p>
<p>save keystrokes in spesific file </p>
<p>hide from lsmod </p>
<p>unhide from lsmod </p>
<p>cover the tracks by cleaning kernel segments</p>
<p>remove the module from /sys/modules directory </p>
<h2>how to use</h2>
<p>clone the repo, using git clone comannd</p>
<p>cd keylogger</p>
<p>make</p>
<p>sudo insmod kelogger.ko</p>
<h4>how to see the kyloging</h4>
<p>cd /sys/kernel/debug/keylogger</p>
<p>cat keyloging</p>
<h5>how to hide and unhide the module</h5>
<p><b>remember that after hiding the module will remove form /proc/modules and will not be recover, im working on fix it</b><p>
<p>cd /sys/kernel/debug/keylogger</p>
<p>./hide</p>
