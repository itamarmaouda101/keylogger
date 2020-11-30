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
<h4>Digital Wishper article about the project</h4>
<p>during the project i created a little article that discribe my R&D journey</p>
<p>inside my article im explaining the main idea of the project and how i achieve it 
this is the link for the article in the digital wishper magazin: https://www.digitalwhisper.co.il/files/Zines/0x7C/DW124-5-LinuxKernelKeyLogger.pdf</p>
<h5>Note: Don't use this code for illegal activities, it is only meant to teach about rootkits in cyber security education point of view. I am not responsible for any harm to unauthorised system.</h5>
