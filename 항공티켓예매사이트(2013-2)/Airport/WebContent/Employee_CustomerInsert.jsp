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
	String ID = request.getParameter("ID");
	String select = request.getParameter("select");	
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	int sel = Integer.valueOf(select);	

	%><form action="Employee_CustomerInsert_continue.jsp" method="POST" >
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>ID</th><th>Password</th><th>이름</th><th>나이</th><th>성별</th><th>주소</th><th>전화번호</th><th>클래스</th><th>마일리지</th>
	</tr>
	<%
	String C_ID[] = new String[10];
	String C_PS[] = new String[10];
	String C_Name[] = new String[10];
	String C_Age[] = new String[10];
	String C_Gender[] = new String[10];
	String C_Address[] = new String[10];
	String C_Phonenumber[] = new String[10];
	String C_Rank[] = new String[10];
	String C_Mileage[] = new String[10];
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select C_ID, C_PS, C_Name, C_Age, C_Gender, C_Address, C_Phonenumber, C_Rank, C_Mileage from customer");
		int i = 0;
		while (rs.next()){
			C_ID[i] = rs.getString("C_ID");
			C_PS[i] = rs.getString("C_PS");			
			C_Name[i] = new String(rs.getString("C_Name").getBytes("8859_1"));
			C_Age[i] = rs.getString("C_Age");
			C_Gender[i] = rs.getString("C_Gender");
			C_Address[i] = new String(rs.getString("C_Address").getBytes("8859_1"));
			C_Phonenumber[i] = rs.getString("C_Phonenumber");	
			C_Rank[i] = rs.getString("C_Rank");	
			C_Mileage[i] = rs.getString("C_Mileage");	
			i++;
		}
		%>	
		<tr><td><%=C_ID[sel]%></td><td><%=C_PS[sel]%></td><td><%=C_Name[sel]%></td><td><%=C_Age[sel] %></td><td><%=C_Gender[sel]%>
		</td><td><%=C_Address[sel] %></td><td><%=C_Phonenumber[sel]%></td><td><%=C_Rank[sel]%></td><td><%=C_Mileage[sel]%></td>			
		</tr>				
		<%
	
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
	<input type="hidden" name="C_ID" value="<%=C_ID[sel]%>">
	<input type="hidden" name="ID" value="<%=ID%>">	
	</form>	
		
	<form action="Employee_CustomerDelete.jsp" method="POST" >
	<input type="hidden" name="C_ID" value="<%=C_ID[sel]%>">	
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="삭제">		
	</form>	
	<input type = "button" value = "뒤로"
				onclick = "history.go(-1)">










</body>
</html>