<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%String tmpID = request.getParameter("ID"); %>
				<form action="Customer.jsp" method="POST">
				<input type="hidden" name="ID" value="<%=tmpID%>">
				<input type="submit" value="������������">				
				</form>
				
				<form action="Flight.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=tmpID%>">
				<input type="hidden" name="LoginCheck" value="1">
				<input type="submit" value="�װ��� �˻�">				
				</form>
				
				<form action="Customer_Cart_View.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=tmpID%>">
				<input type="submit" value="īƮ ����">				
				</form>	
				
				<form action="Customer_Reservation_View.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=tmpID%>">
				<input type="submit" value="���� ��Ȳ">				
				</form>	
				
				<form action="Login.jsp" method="POST">
<input type="submit" value="Logout">
</form>
</body>
</html>