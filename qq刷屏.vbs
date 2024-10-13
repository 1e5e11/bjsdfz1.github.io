Dim Shell
Set Shell=WScript.CreateObject("WScript.Shell")
Shell.Run "C:\Users\Public\Desktop\a"
WScript.Sleep 1000
for i=1 to 100
WScript.Sleep 30
Shell.SendKeys "^v"
WScript.Sleep 10
Shell.SendKeys "~"
next
