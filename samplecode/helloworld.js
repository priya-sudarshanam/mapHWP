function sayHello()
{
  document.getElementById("hello").innerHTML = '<b>Hello World</b>';
  document.getElementById("changecolor").innerHTML = '<b><font color="red">Hello World</font></b>';
}
window.onload = sayHello;
