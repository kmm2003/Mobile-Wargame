import frida, sys

def on_message(message, data):
	if message['type'] == 'send':
		print("[*] {0}".format(message['payload']))
	else:
		print(message)

PACKAGE_NAME = "com.dreamhack.reversing"

jscode = """
console.log("[*] Start Hooking");

Java.perform(function() {
    var bypassExit = Java.use("java.lang.System"); // system Class Hook
    bypassExit.exit.implementation = function (){ // exit() overwrite
        console.log("[*] System.exit() is called"); // "Root Detect" 우회
    }
    var bypassDebugging = Java.use("android.os.Debug"); // Debugging Check
    bypassDebugging.isDebuggerConnected.implementation = function (){
        console.log("[*] isDebuggerConnected() is called");
        return true;       
    }
});

console.log(Module.findBaseAddress('libreversing.so'));

setTimeout(function() {
  Interceptor.attach(Module.findBaseAddress('libreversing.so').add(0xCBF0), {
    onEnter: function(args) {
    },
    onLeave: function(retval) {
      console.log("Secret generator on leave");
      console.log(hexdump(retval, {
        offset: 0,
        length: 0x1c,
        header: true,
        ansi: true
      }));
    }
  });
}, 3000);
"""

try:
    device = frida.get_usb_device(timeout=10)
    pid = device.spawn([PACKAGE_NAME]) 
    print("App is starting ... pid : {}".format(pid))
    process = device.attach(pid)
    device.resume(pid)
    script = process.create_script(jscode)
    script.on('message',on_message)
    print('[*] Running Frida')
    script.load()
    sys.stdin.read()
except Exception as e:
    print(e)