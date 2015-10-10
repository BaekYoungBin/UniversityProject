<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%String ID = request.getParameter("ID");
String Plane_Type = request.getParameter("Plane_Type");
String Origin = request.getParameter("Origin");
String select = request.getParameter("select");
%>


	<form action="Payment.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">	
	<input type="hidden" name="select" value="<%=select%>">	

	<input type="submit" value="결제">
</form>

<form action="Customer_Reservation_Delete.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">	
	<input type="hidden" name="select" value="<%=select%>">	
	<input type="submit" value="삭제">
	</form>
	
</body>
</html>