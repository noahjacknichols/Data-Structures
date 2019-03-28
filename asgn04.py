"""
asgn04.py
Noah Nichols
"""

def table_info(conn, table_schema, table_name=None):
    """
    -------------------------------------------------------
    Queries information_schema.TABLES for metadata.
    Use: rows = table_info(conn, table_schema)
    Use: rows = table_info(conn, table_schema, table_name=v1)
    -------------------------------------------------------
    Parameters:
        conn - a database connection (Connect)
        table_schema - the database table schema (str)
        table_name - a DCRIS table name (str)
    Returns:
        rows - a list of data from the TABLE_NAME, TABLE_TYPE, TABLE_ROWS, 
        and TABLE_COMMENT fields. Order by TABLE_NAME.
        If table_name is None, list all tables. (list of ?)
    -------------------------------------------------------
    """

    if table_name == None:
        sql = """"
        SELECT TABLE_NAME, TABLE_TYPE, TABLE_ROWS, TABLE_COMMENT
        FROM INFORMATION_SCHEME.TABLES AS t
        WHERE t.table_schema = %s
        ORDER BY table_name
        """
        params = (table_schema,)
        conn.cursor.execute(sql, params)
    else:
        sql = """
        SELECT TABLE_NAME, TABLE_TYPE, TABLE_ROWS, TABLE_COMMENT
        FROM INFORMATION_SCHEMA.TABLES AS t
        WHERE t.table_schema = %s AND t.table_name = %s
        ORDER BY table_name
        """
        params = (table_schema, table_name,)
        conn.cursor.execute(sql, params)
    
    rows = conn.cursor.fetchall()
    return rows

def column_info(conn, table_schema, table_name=None):
    """
    -------------------------------------------------------
    Queries information_schema.COLUMNS for metadata.
    Use: rows = column_info(conn, table_schema)
    Use: rows = column_info(conn, table_schema, table_name=v1)
    -------------------------------------------------------
    Parameters:
        conn - a database connection (Connect)
        table_schema - the database table schema (str)
        table_name - a DCRIS table name (str)
    Returns:
        rows - a list of data from the TABLE_NAME, COLUMN_NAME, IS_NULLABLE, 
        and DATA_TYPE fields. Order by TABLE_NAME, COLUMN_NAME.
        If table_name is None, list all tables and their columns. (list of ?)
    -------------------------------------------------------
    """

    if table_name == None:
        sql = """
        SELECT TABLE_NAME, COLUMN_NAME, IS_NULLABLE, DATA_TYPE
        FROM information_schema.columns as c
        WHERE c.table_schema = %s
        ORDER BY table_name, column_name
        """
        params = (table_schema,)
        conn.cursor.execute(sql, params)

    else:    
        sql = """
        SELECT TABLE_NAME, COLUMN_NAME, IS_NULLABLE, DATA_TYPE
        FROM information_schema.columns AS c
        WHERE c.table_schema = %s AND c.table_name = %s
        ORDER BY TABLE_NAME, COLUMN_NAME 
        """
        params = (table_schema, table_name,)
        conn.cursor.execute(sql, params)

    rows = conn.cursor.fetchall()
    return rows

def constraint_info(conn, table_schema, constraint_type=None):
    """
    -------------------------------------------------------
    Queries information_schema.TABLE_CONSTRAINTS for metadata.
    Use: rows = constraint_info(conn, table_schema)
    Use: rows = constraint_info(conn, table_schema, constraint_type=v1)
    -------------------------------------------------------
    Parameters:
        conn - a database connection (Connect)
        table_schema - the database table schema (str)
        constraint_type - a database constraint type (str)
    Returns:
        rows - a list of data from the CONSTRAINT_NAME, TABLE_NAME, 
        and CONSTRAINT_TYPE. Order by CONSTRAINT_NAME, TABLE_NAME.
        If constraint_type is None, list all constraints. (list of ?)
    -------------------------------------------------------
    """

    if constraint_type == None:
        sql = """
        SELECT CONSTRAINT_NAME, TABLE_NAME, CONSTRAINT_TYPE
        FROM information_schema.table_constraints AS s
        WHERE s.table_schema = %s
        ORDER BY CONSTRAINT_NAME, TABLE_NAME
        """
        params = (table_schema,)
        conn.cursor.execute(sql, params)
    else:
        sql = """
        SELECT CONSTARINT_NAME, TABLE_NAME, CONSTRAINT_TYPE
        FROM information_schema.table_constraints AS s
        WHERE s.table_schema = %s AND s.constraint_type = %s
        ORDER BY CONSTRAINT_NAME, TABLE_NAME 
        """
        params = (table_schema, constraint_type,)
        conn.cursor.execute(sql, params)
    
    rows = conn.cursor.fetchall()
    return rows
    
def foreign_key_info(conn, constraint_schema, table_name=None, ref_table_name=None):
    """
    -------------------------------------------------------
    Queries information_schema.REFERENTIAL_CONSTRAINTS for metadata.
    Use: rows = foreign_key_info(conn, constraint_schema)
    Use: rows = foreign_key_info(conn, constraint_schema, table_name=v1)
    Use: rows = foreign_key_info(conn, constraint_schema, ref_table_name=v2)
    Use: rows = foreign_key_info(conn, constraint_schema, table_name=v1, ref_table_name=v2)
    -------------------------------------------------------
    Parameters:
        conn - a database connection (Connect)
        constraint_schema - the database constraint schema (str)
        table_name - a DCRIS table name (str)
        ref_table_name - a DCRIS table name (str)
    Returns:
        rows - a list of data from the CONSTRAINT_NAME, UPDATE_RULE, DELETE_RULE, 
        TABLE_NAME, and REFERENCED_TABLE_NAME fields. Order by CONSTRAINT_NAME.
        If table_name and ref_table_name are None, list all rows. (list of ?)
    -------------------------------------------------------
    """

    if table_name == None and ref_table_name == None:
        sql = """
        SELECT CONSTRAINT_NAME, UPDATE_RULE, DELETE_RULE, TABLE_NAME, REFERENCED_TABLE_NAME
        FROM information_schema.referential_constraints as r
        WHERE r.constraint_schema = %s
        ORDER BY CONSTRAINT_NAME
        """
        params = (constraint_schema,)
        conn.cursor.execute(sql, params)
    elif table_name != None and ref_table_name == None:
        sql = """
        SELECT CONSTRAINT_NAME, UPDATE_RULE, DELETE_RULE, TABLE_NAME, REFERENCED_TABLE_NAME
        FROM information_schema.referential_constraints as r
        WHERE r.constraint_schema = %s AND r.TABLE_NAME = %s
        ORDER BY CONSTRAINT_NAME
        """
        params = (constraint_schema, table_name,)
        conn.cursor.execute(sql, params)
    elif table_name == None and ref_table_name != None:
        sql = """
        SELECT CONSTRAINT_NAME, UPDATE_RULEM DELETE_RULE, TABLE_NAME, REFERENCED_TABLE_NAME
        FROM information_schema.referential_constraints as r
        WHERE r.constraint_schema = %s AND r.REFERENCED_TABLE_NAME = %s
        ORDER BY CONSTRAINT_NAME
        """
        params = (constraint_schema, ref_table_name,)
        conn.cursor.execute(sql, params)
    else:
        sql = """
        SELECT CONSTRAINT_NAME, UPDATE_RULE, DELETE_RULE, TABLE_NAME, REFERENCED_TABLE_NAME
        FORM information_schema.referential_constraints as r
        WHERE r.constraint_schema = %s AND r.TABLE_NAME = %s AND r.REFERENCED_TABLE_NAME = %s
        ORDER BY CONSTRAINT_NAME
        """
        params = (constraint_schema, table_name, ref_table_name,)
        conn.cursor.execute(sql, params)
    
    rows = conn.cursor.fetchall()
    return rows

def key_info(conn, constraint_schema, table_name=None, ref_table_name=None):
    """
    -------------------------------------------------------
    Queries information_schema.KEY_COLUMN_USAGE for metadata.
    Use: rows = key_info(conn, constraint_schema)
    Use: rows = key_info(conn, constraint_schema, table_name=v1)
    Use: rows = key_info(conn, constraint_schema, ref_table_name=v2)
    Use: rows = key_info(conn, constraint_schema, table_name=v1, ref_table_name=v2)
    -------------------------------------------------------
    Parameters:
        conn - a database connection (Connect)
        constraint_schema - the database constraint schema (str)
        table_name - a DCRIS table name (str)
        ref_table_name - a DCRIS table name (str)
    Returns:
        rows - a list of data from the CONSTRAINT_NAME, TABLE_NAME, COLUMN_NAME, 
        REFERENCED_TABLE_NAME, and REFERENCED_COLUMN_NAME fields. Order by 
        TABLE_NAME, COLUMN_NAME. 
        If table_name and ref_table_name are None, list all rows. (list of ?)
    -------------------------------------------------------
    """

    if table_name == None and ref_table_name == None:
        sql = """
        SELECT CONSTRAINT_NAME, TABLE_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME
        FROM information_schema.key_column_usage as k
        WHERE k.constraint_schema  %s
        ORDER BY TABLE_NAME, COLUMN_NAME
        """
        params = (constraint_schema,)
        conn.cursor.execute(sql, params)
    elif table_name != None and ref_table_name == None:
        sql = """
        SELECT CONSTRAINT_NAME, TABLE_NAME, COLUMN_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME
        FROM information_schema.key_column_usage as k
        WHERE k.constraint_schema = %s AND k.TABLE_NAME = %s
        ORDER BY TABLE_NAME, COLUMN_NAME 
        """
        params = (constraint_schema, table_name,)
        conn.cursor.execute(sql, params)
    elif table_name == None and ref_table_name != None:
        sql = """
        SELECT CONSTRAINT_NAME, TABLE_NAME, COLUMN_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME
        FROM information_schema.key_column_usage as k
        WHERE k.constraint_schema = %s AND k.REFERENCED_TABLE_NAME = %s
        ORDER BY TABLE_NAME, COLUMN_NAME
        """
        params = (constraint_schema, ref_table_name)
        conn.cursor.execute(sql, params)
    else:
        sql = """
        SELECT CONSTRAINT_NAME, TABLE_NAME, COLUMN_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME
        FROM information_schema.key_column_usage as k
        WHERE k.constraint_schema = %s AND k.TABLE_NAME = %s AND k.REFERENCED_TABLE_NAME = %s
        ORDER BY TABLE_NAME, COLUMN_NAME
        """
        params = (constraint_schema, table_name, ref_table_name,)
        conn.cursor.execute(sql, params)
    
    rows = conn.cursor.fetchall()
    return rows