<h1>linux keylogger</h1>
<p>
  this is a simple linux keylogger
  that is part of my rootkit project
</p>
<h2>what is it doing?</h2>
<li> save keystrokes in spesific file</li> 
<li> hide from lsmod</li> 
<li> unhide from lsmod </li>
<li> cover the tracks by cleaning kernel segments</li>
<li> remove the module from /sys/modules directory </li>
<h2>how to use</h2>
<p><b>for using the module u need to be super user</b></p>
<ol>
<li><mark>clone the repo, using git clone comannd</mark></li>
<li><mark>cd keylogger</mark></li>
<li><mark>make</mark></li>
<li><mark>sudo insmod kelogger.ko</mark></li>
</ol>
<h2>how to see the keyloging</h2>
<ol>
<li>cd /sys/kernel/debug/keylogger</li>
<li>cat ./keyloging</li>
</ol>
<h2>how to hide and unhide the module</h2>
<p><b>remember that after hiding the module will remove form /proc/modules and will not be recover, im working on fix it</b><p>
<ol>
<li>cd /sys/kernel/debug/keylogger</li>
<li>./hide</li>
</ol>
<h3>Tested on Linux ubuntu 5.4.0-52-generic </h3>
