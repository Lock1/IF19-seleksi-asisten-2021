
const vertexglsrc = `
    attribute vec4 aVertexPosition;
    attribute vec4 aVertexColor;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    varying lowp vec4 vColor;

    void main() {
        gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
        vColor = aVertexColor;
    }
`;

const fragmentglsrc = `
    varying lowp vec4 vColor;

    void main(void) {
        gl_FragColor = vColor;
    }
`;






function InitBuffer(gl) {
    // Setup position buffer
    const positionArray = [
        -3.0, 1.0, 1.0,
        -3.0, -1.0, 1.0,
        -1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0,

        -3.0, 1.0, -1.0,
        -1.0, 1.0, -1.0,
        -3.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,

        // Tetra
        1.0, 1.0, 1.0,
        2.0, 1.0, 1.0,
        1.5, 1.866, 1.0,
        1.5, 1.2886, 1.801

    ];

    const posBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, posBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positionArray), gl.STATIC_DRAW);


    // Setup color buffer
    const colorArray = [
        0.5, 0.0, 1.0, 1.0,
        0.2, 1.0, 1.0, 1.0,
        0.0, 0.5, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,

        1.0, 0.2, 1.0, 1.0,
        0.2, 0.6, 1.0, 1.0,
        0.4, 0.0, 0.5, 1.0,
        0.0, 1.0, 1.0, 1.0,

        0.4, 0.0, 0.5, 1.0,
        0.0, 1.0, 1.0, 1.0,
        0.4, 0.0, 0.5, 1.0,
        0.0, 1.0, 1.0, 1.0
    ];

    const colBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, colBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colorArray), gl.STATIC_DRAW);



    // Setup index
    const indexArray = [
        0, 1, 2,    1, 2, 3,
        0, 1, 4,    1, 4, 6,
        1, 6, 7,    1, 7, 3,

        5, 4, 6,    5, 7, 6,
        2, 5, 4,    4, 2, 0,
        2, 5, 3,    7, 5, 3,

        // Tetra
        8, 9, 10,   8, 9, 11,
        8, 10, 11,   9, 10, 11

    ];

    const indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexArray), gl.STATIC_DRAW);


    return { position: posBuffer, color: colBuffer, indices: indexBuffer };
}





function drawScene(gl, pInfo, buffer) {
    // Clear screen and setup black background
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clearDepth(1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);


    // Set camera
    const fov = (45 * Math.PI) / 180;
    const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
    const projectionMatrix = mat4.create();
    mat4.perspective(projectionMatrix, fov, aspect, 0.1, 100.0);

    const modelViewMatrix = mat4.create();
    mat4.translate(modelViewMatrix, modelViewMatrix, [-0.0, 0.0, -6.0]);

    // Rotation
    mat4.rotate(modelViewMatrix, modelViewMatrix, currentRotation, [1, 0, 0]);
    mat4.rotate(modelViewMatrix, modelViewMatrix, currentRotation*0.4, [0, 1, 0]);


    // Bind vertex position
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.position);
    gl.vertexAttribPointer(pInfo.attribLocations.vertexPosition, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(pInfo.attribLocations.vertexPosition);

    // Bind vertex color
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.color);
    gl.vertexAttribPointer(pInfo.attribLocations.vertexColor, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(pInfo.attribLocations.vertexColor);

    // Bind vertex index
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indices);

    // Draw scene
    gl.useProgram(pInfo.program);

    gl.uniformMatrix4fv(pInfo.uniformLocations.projectionMatrix, false, projectionMatrix);
    gl.uniformMatrix4fv(pInfo.uniformLocations.modelViewMatrix, false, modelViewMatrix);

    // gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.drawElements(gl.TRIANGLES, 48, gl.UNSIGNED_SHORT, 0);
}





let currentRotation = 0.0;

var gl;
var shaderGL;
var programInfo;
var buffer;

let then = 0;

function render(now) {
    now *= 0.001;
    const delta = now - then;
    then = now;

    drawScene(gl, programInfo, buffer, delta);
    currentRotation += delta;

    requestAnimationFrame(render);
}

requestAnimationFrame(render);


function main() {
    const canvas = document.querySelector("#canv1");
    // Initialize the GL context
    gl = canvas.getContext("webgl");

    // Only continue if WebGL is available and working
    if (gl === null) {
        alert("Unable to initialize WebGL. Your browser or machine may not support it.");
        return;
    }


    shaderGL = InitShader(gl, vertexglsrc, fragmentglsrc);

    programInfo = {
        program: shaderGL,
        attribLocations: {
            vertexPosition: gl.getAttribLocation(shaderGL, 'aVertexPosition'),
            vertexColor: gl.getAttribLocation(shaderGL, 'aVertexColor')
        },
        uniformLocations: {
            projectionMatrix: gl.getUniformLocation(shaderGL, 'uProjectionMatrix'),
            modelViewMatrix: gl.getUniformLocation(shaderGL, 'uModelViewMatrix')
        }
    };

    buffer = InitBuffer(gl);
    // drawScene(gl, programInfo, InitBuffer(gl));
}

window.onload = main;
