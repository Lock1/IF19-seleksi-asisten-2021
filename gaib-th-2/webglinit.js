function InitShader(gl, vssrc, fssrc) {
    const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vssrc);
    const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fssrc);

    const shader = gl.createProgram();
    gl.attachShader(shader, vertexShader);
    gl.attachShader(shader, fragmentShader);
    gl.linkProgram(shader);

    if (!gl.getProgramParameter(shader, gl.LINK_STATUS)) {
        alert('Unable to initialize the shader program: ' + gl.getProgramInfoLog(shader));
        return null;
    }

    return shader;
}



function loadShader(gl, type, src) {
    const shader = gl.createShader(type);

    gl.shaderSource(shader, src);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
    }

    return shader;
}
