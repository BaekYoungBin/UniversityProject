<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%String A_ID = request.getParameter("ID"); %>
<form action="Flight.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=A_ID%>">
				<input type="hidden" name="LoginCheck" value="2">
				 
				<input type="submit" value="항공편 검색">				
				</form>	
				<form action="Agency_Cart_View.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=A_ID%>">
				
				<input type="submit" value="카트 보기">				
				</form>	
				<form action="Agency_Reservation_View.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=A_ID%>">
				<input type="submit" value="예약 현황">				
				</form>	
				<form action="Login.jsp" method="POST">
<input type="submit" value="Logout">
</form>
</body>
</html>