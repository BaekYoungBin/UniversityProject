<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%String E_ID = request.getParameter("ID"); %>
<form action="EmployeeSearchCustomer.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=E_ID%>">

				<input type="submit" value="������ �˻�/����">				
				</form>	
				<form action="EmployeeSearchFlight.jsp" method="POST" >
				<input type="submit" value="�װ��� ����">				
				</form>	
				<form action="Flight_Reservation.jsp" method="POST" >
			
				<input type="submit" value="�װ��� �����Ȳ">				
				</form>	
				<form action="A_Flight_Reservation.jsp" method="POST" >
			
				<input type="submit" value="����� �����Ȳ">				
				</form>	
				<form action="Employee_Agency_Enrollment.jsp" method="POST" >
				<input type="hidden" name="ID" value="<%=E_ID%>">

				<input type="submit" value="����� ���">				
				</form>	
				<form action="Login.jsp" method="POST">
<input type="submit" value="Logout">
</form>
</body>
</html>