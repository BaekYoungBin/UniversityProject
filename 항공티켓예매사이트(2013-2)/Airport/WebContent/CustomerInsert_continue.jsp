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
	
	String C_ID = request.getParameter("ID");
	String I_PS = request.getParameter("PS");
	String I_Name = request.getParameter("Name");
	String I_Age = request.getParameter("Age");
	String I_Gender = request.getParameter("Gender");
	String I_Address = request.getParameter("Address");
	String I_Phone = request.getParameter("Phone");
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	
	 if(I_PS.length() > 20 || I_PS.length() <4)
		{
			out.print("비밀번호를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Name.length() >10 || I_Name.length() <2)
		{
			out.print("이름을 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Age.length() > 3 || I_Age.length() <1)
		{
			out.print("나이를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Address.length()>60 || I_Address.length()<2)
		{
			out.print("주소를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
		else if(I_Phone.length() > 15 || I_Phone.length()<8)
		{
			out.print("전화번호를 확인해주세요");
			%>
				<input type = "button" value = "확인"
						onclick = "history.go(-1)">
			<%
		}
			
	try{
		
				
			DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
			Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
			Statement stmt = conn.createStatement();
			ResultSet rs;			
				rs = stmt.executeQuery("update CUSTOMER set C_PS = '"+I_PS +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_NAME = '"+I_Name +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_AGE = '"+I_Age +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_ADDRESS = '"+I_Address +"' where C_ID = '" + C_ID +"'");
				rs = stmt.executeQuery("update CUSTOMER set C_PHONENUMBER = '"+I_Phone +"' where C_ID = '" + C_ID +"'");
				
			
			 rs.close();
			stmt.close();
			conn.close();
			
	}
	catch(Exception e) {
		e.printStackTrace();
	}
		
		
		
		
		
		%>
		
		<form action="CustomerMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=C_ID%>">
<input type="submit" value="HOME">
</form>
</body>
</html>