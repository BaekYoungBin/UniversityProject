<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>YB�װ�</title>
</head>
<body>
<%@ page import = "java.io.*" %>

	<form  action = "LoginCheck.jsp" method = "POST">
	<h2> �װ� ���� �ý����Դϴ�. </h2>
	<input type = "radio" name = "LoginType" value = "Customer" checked>�Ϲ�ȸ��
	<input type = "radio" name = "LoginType" value = "Manager">������
	<input type = "radio" name = "LoginType" value = "Employee">�װ��� ����
	<input type = "radio" name = "LoginType" value = "Agency"> �����
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
		<td> ID </td>
		<td> <input type = "text" name = "ID"> </td>
	</tr>
	<tr>
	<td> Password  </td>
	<td> <input type = "password" name = "pwd"> <BR>
	</td>
		</tr>
		</table>	
		<input type = "submit" value = "�α���">	
			</form>
<form  action = "Customer_Enrollment.jsp" method = "POST">
<input type = "submit" value = "ȸ������">	
</form>

</body>
</html>
