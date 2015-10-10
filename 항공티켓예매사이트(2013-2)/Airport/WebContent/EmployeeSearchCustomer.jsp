<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%
		String tmpID = request.getParameter("ID");	
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	%><form action="Employee_CustomerInsert.jsp" method="POST" >
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>ID</th><th>Password</th><th>이름</th><th>나이</th><th>성별</th><th>주소</th><th>전화번호</th><th>클래스</th><th>마일리지</th><th>선택</th>
	</tr>
	<%
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select C_ID, C_PS, C_Name, C_Age, C_Gender, C_Address, C_Phonenumber, C_Rank, C_Mileage from customer");
		int i = 0;
		while (rs.next()){
			String C_ID = rs.getString("C_ID");
			String C_PS = rs.getString("C_PS");
			String C_Name = new String(rs.getString("C_Name").getBytes("8859_1"));
			String C_Age = rs.getString("C_Age");
			String C_Gender = rs.getString("C_Gender");
			String C_Address = new String(rs.getString("C_Address").getBytes("8859_1"));
			String C_Phonenumber = rs.getString("C_Phonenumber");
			String C_Rank = rs.getString("C_Rank");
			String C_Mileage = rs.getString("C_Mileage");
			%>	
			<tr><td><%=C_ID%></td><td><%=C_PS%></td><td><%=C_Name%></td><td><%=C_Age %></td><td><%=C_Gender%>
			</td><td><%=C_Address %></td><td><%=C_Phonenumber%></td><td><%=C_Rank%></td><td><%=C_Mileage%></td><td>
			<% if(i == 0){
				%>				
			<input type = "radio" name = "select" value = "<%=i%>" checked>						
				<%
				
			}
			else
			{
%>
				<input type = "radio" name = "select" value = "<%=i%>">			
				<%
			}
			%>
			</td></tr>
			<%	
			i++;
		}
	
	
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
	
	
	
	%>
	
	
</table>	

	<input type="submit" value="수정">
	<input type="hidden" name="ID" value="<%=tmpID%>">
	</form>	
	<input type = "button" value = "뒤로"
				onclick = "history.go(-1)">
	<form action="Login.jsp" method="POST" >
	<input type="submit" value="Logout">
	</form>
</body>
</html>